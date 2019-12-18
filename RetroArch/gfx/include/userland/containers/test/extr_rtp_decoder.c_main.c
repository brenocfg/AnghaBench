#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_8__ {int status; } ;
typedef  TYPE_1__ VC_CONTAINER_IO_T ;

/* Variables and functions */
 scalar_t__ ESCAPE_CHARACTER ; 
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  LOG_INFO (int /*<<< orphan*/ *,char*,size_t) ; 
 scalar_t__ LOWEST_VERBOSITY ; 
 scalar_t__ MAXIMUM_BUFFER_SIZE ; 
 scalar_t__ MINIMUM_BUFFER_SPACE ; 
 int /*<<< orphan*/  VC_CONTAINER_CONTROL_IO_SET_READ_TIMEOUT_MS ; 
#define  VC_CONTAINER_ERROR_CONTINUE 129 
 int /*<<< orphan*/  VC_CONTAINER_IO_MODE_READ ; 
 int /*<<< orphan*/  VC_CONTAINER_IO_MODE_WRITE ; 
#define  VC_CONTAINER_SUCCESS 128 
 int /*<<< orphan*/  decode_packet (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ do_print_usage ; 
 size_t fetch_u32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  increase_read_buffer_size (TYPE_1__*) ; 
 scalar_t__ malloc (scalar_t__) ; 
 int marker_bit_set (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ nb_char_available () ; 
 scalar_t__ nb_get_char () ; 
 int /*<<< orphan*/  nb_set_nonblocking_input (int) ; 
 scalar_t__ packet_save_file ; 
 scalar_t__ packet_save_is_pktfile ; 
 int /*<<< orphan*/  parse_command_line (int,char**) ; 
 int /*<<< orphan*/  print_usage (char*) ; 
 scalar_t__ read_uri ; 
 int /*<<< orphan*/  store_u32 (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  vc_container_io_close (TYPE_1__*) ; 
 int /*<<< orphan*/  vc_container_io_control (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* vc_container_io_open (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t vc_container_io_read (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 
 size_t vc_container_io_write (TYPE_1__*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ verbosity ; 

int main(int argc, char **argv)
{
   int result = 0;
   uint8_t *buffer = NULL;
   VC_CONTAINER_IO_T *read_io = NULL;
   VC_CONTAINER_IO_T *write_io = NULL;
   VC_CONTAINER_STATUS_T status;
   size_t received_bytes;
   bool ready = true;
   uint32_t available_bytes;
   uint8_t *packet_ptr;

   parse_command_line(argc, argv);

   if (do_print_usage || !read_uri)
   {
      print_usage(argv[0]);
      result = 1; goto tidyup;
   }

   buffer = (uint8_t *)malloc(MAXIMUM_BUFFER_SIZE);
   if (!buffer)
   {
      LOG_ERROR(NULL, "Allocating %d bytes for the buffer failed", MAXIMUM_BUFFER_SIZE);
      result = 2; goto tidyup;
   }

   read_io = vc_container_io_open(read_uri, VC_CONTAINER_IO_MODE_READ, &status);
   if (!read_io)
   {
      LOG_ERROR(NULL, "Opening <%s> for read failed: %d", read_uri, status);
      result = 3; goto tidyup;
   }

   increase_read_buffer_size(read_io);

   if (packet_save_file)
   {
      write_io = vc_container_io_open(packet_save_file, VC_CONTAINER_IO_MODE_WRITE, &status);
      if (!write_io)
      {
         LOG_ERROR(NULL, "Opening <%s> for write failed: %d", packet_save_file, status);
         result = 4; goto tidyup;
      }
      if (!packet_save_is_pktfile)
      {
         store_u32(buffer, 0x50415753);
         vc_container_io_write(write_io, buffer, sizeof(uint32_t));
      }
   }

   /* Use non-blocking I/O for both network and console */
   vc_container_io_control(read_io, VC_CONTAINER_CONTROL_IO_SET_READ_TIMEOUT_MS, 20);
   nb_set_nonblocking_input(1);

   packet_ptr = buffer;
   available_bytes = MAXIMUM_BUFFER_SIZE - sizeof(uint32_t);
   while (ready)
   {
      /* Read a packet and store its length in the word before it */
      received_bytes = vc_container_io_read(read_io, packet_ptr + sizeof(uint32_t), available_bytes);
      if (received_bytes)
      {
         bool packet_has_marker;

         store_u32(packet_ptr, received_bytes);
         packet_ptr += sizeof(uint32_t);
         packet_has_marker = marker_bit_set(packet_ptr, received_bytes);
         packet_ptr += received_bytes;
         available_bytes -= received_bytes + sizeof(uint32_t);

         if (packet_has_marker || (available_bytes < MINIMUM_BUFFER_SPACE))
         {
            uint8_t *decode_ptr;

            if (write_io && !packet_save_is_pktfile)
            {
               uint32_t total_bytes = packet_ptr - buffer;
               if (vc_container_io_write(write_io, buffer, total_bytes) != total_bytes)
               {
                  LOG_ERROR(NULL, "Error saving packets to file");
                  break;
               }
               if (verbosity >= LOWEST_VERBOSITY)
                  LOG_INFO(NULL, "Written %u bytes to file", total_bytes);
            }

            for (decode_ptr = buffer; decode_ptr < packet_ptr;)
            {
               received_bytes = fetch_u32(decode_ptr);
               decode_ptr += sizeof(uint32_t);

               if (write_io && packet_save_is_pktfile)
               {
                  if (vc_container_io_write(write_io, buffer, received_bytes) != received_bytes)
                  {
                     LOG_ERROR(NULL, "Error saving packets to file");
                     break;
                  }
                  if (verbosity >= LOWEST_VERBOSITY)
                     LOG_INFO(NULL, "Written %u bytes to file", received_bytes);
               }

               if (!decode_packet(decode_ptr, received_bytes))
               {
                  LOG_ERROR(NULL, "Failed to decode packet");
                  break;
               }
               decode_ptr += received_bytes;
            }

            /* Reset to start of buffer */
            packet_ptr = buffer;
            available_bytes = MAXIMUM_BUFFER_SIZE - sizeof(uint32_t);
         }
      }

      if (nb_char_available())
      {
         if (nb_get_char() == ESCAPE_CHARACTER)
            ready = false;
      }

      switch (read_io->status)
      {
      case VC_CONTAINER_SUCCESS:
      case VC_CONTAINER_ERROR_CONTINUE:
         break;
      default:
         ready = false;
      }
   }

   nb_set_nonblocking_input(0);

tidyup:
   if (write_io)
      vc_container_io_close(write_io);
   if (read_io)
      vc_container_io_close(read_io);
   if (buffer)
      free(buffer);

   return result;
}