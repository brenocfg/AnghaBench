#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  unsigned int int16_t ;

/* Variables and functions */
 scalar_t__ BASIC_HEADER_VERBOSITY ; 
 int CSRC_COUNT_MASK ; 
 int EXTENSION_ID_SHIFT ; 
 int EXTENSION_LENGTH_MASK ; 
 scalar_t__ FULL_HEADER_VERBOSITY ; 
 scalar_t__ FULL_PACKET_VERBOSITY ; 
 int HAS_EXTENSION ; 
 int HAS_MARKER ; 
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  LOG_INFO (int /*<<< orphan*/ *,char*,...) ; 
 int PAYLOAD_TYPE_MASK ; 
 int /*<<< orphan*/  dump_bytes (int const*,size_t) ; 
 scalar_t__ expected_next_seq_num ; 
 scalar_t__ network_to_host_16 (int const*) ; 
 unsigned int network_to_host_32 (int const*) ; 
 int seen_first_packet ; 
 scalar_t__ verbosity ; 

__attribute__((used)) static bool decode_packet(const uint8_t *buffer, size_t buffer_len)
{
   uint8_t flags;
   uint8_t payload_type;
   uint16_t seq_num;
   uint32_t timestamp;
   uint32_t ssrc;
   uint32_t csrc_count;

   if (buffer_len < 12)
   {
      LOG_ERROR(NULL, "Packet too small: basic header missing");
      return false;
   }

   flags = buffer[0];
   payload_type = buffer[1];
   seq_num = network_to_host_16(buffer + 2);
   timestamp = network_to_host_32(buffer + 4);
   ssrc = network_to_host_32(buffer + 8);

   if (seen_first_packet && seq_num != expected_next_seq_num)
   {
      int16_t missing_packets = seq_num - expected_next_seq_num;

      LOG_INFO(NULL, "*** Sequence break, expected %hu, got %hu ***", expected_next_seq_num, seq_num);
      if (missing_packets > 0)
         LOG_INFO(NULL, "*** Jumped forward %hd packets ***", missing_packets);
      else
         LOG_INFO(NULL, "*** Jumped backward %hd packets ***", -missing_packets);
   }
   seen_first_packet = true;
   expected_next_seq_num = seq_num + 1;

   /* Dump the basic header information */
   if (verbosity >= BASIC_HEADER_VERBOSITY)
   {
      LOG_INFO(NULL, "Version: %d\nPayload type: %d%s\nSequence: %d\nTimestamp: %u\nSSRC: 0x%8.8X",
            flags >> 6, payload_type & PAYLOAD_TYPE_MASK,
            (const char *)((payload_type & HAS_MARKER) ? " (M)" : ""),
            seq_num, timestamp, ssrc);
   }

   buffer += 12;
   buffer_len -= 12;

   if (verbosity >= FULL_HEADER_VERBOSITY)
   {
      /* Dump the CSRCs, if any */
      csrc_count = flags & CSRC_COUNT_MASK;
      if (csrc_count)
      {
         uint32_t ii;

         if (buffer_len < (csrc_count * 4))
         {
            LOG_ERROR(NULL, "Packet too small: CSRCs missing");
            return false;
         }

         LOG_INFO(NULL, "CSRCs:");
         for (ii = 0; ii < csrc_count; ii++)
         {
            LOG_INFO(NULL, " 0x%8.8X", network_to_host_32(buffer));
            buffer += 4;
            buffer_len -= 4;
         }
      }

      /* Dump any extension, if present */
      if (flags & HAS_EXTENSION)
      {
         uint32_t extension_hdr;
         uint32_t extension_id;
         size_t extension_len;

         if (buffer_len < 4)
         {
            LOG_ERROR(NULL, "Packet too small: extension header missing");
            return false;
         }

         extension_hdr = network_to_host_32(buffer);
         buffer += 4;
         buffer_len -= 4;

         extension_len = (size_t)(extension_hdr & EXTENSION_LENGTH_MASK);
         extension_id = extension_hdr >> EXTENSION_ID_SHIFT;

         if (buffer_len < extension_len)
         {
            LOG_ERROR(NULL, "Packet too small: extension content missing");
            return false;
         }

         LOG_INFO(NULL, "Extension: 0x%4.4X (%u bytes)", extension_id, (unsigned)extension_len);
         dump_bytes(buffer, extension_len);
         buffer += extension_len;
         buffer_len -= extension_len;
      }
   }

   /* And finally the payload data */
   if (verbosity >= FULL_PACKET_VERBOSITY)
   {
      LOG_INFO(NULL, "Data: (%u bytes)", (unsigned)buffer_len);
      dump_bytes(buffer, buffer_len);
   }

   return true;
}