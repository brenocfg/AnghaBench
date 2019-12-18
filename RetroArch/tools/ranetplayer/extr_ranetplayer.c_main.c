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
typedef  int uint32_t ;
struct option {char* member_0; int member_1; char member_3; int /*<<< orphan*/ * member_2; } ;
struct addrinfo {int dummy; } ;

/* Variables and functions */
 int NETPLAY_CMD_INFO ; 
#define  NETPLAY_CMD_INPUT 130 
#define  NETPLAY_CMD_MODE 129 
 int NETPLAY_CMD_MODE_BIT_PLAYING ; 
 int NETPLAY_CMD_MODE_BIT_YOU ; 
 int NETPLAY_CMD_NICK ; 
#define  NETPLAY_CMD_NOINPUT 128 
 int NETPLAY_CMD_PLAY ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_WRONLY ; 
 int RARCH_DEFAULT_PORT ; 
 int /*<<< orphan*/  RECV () ; 
 int /*<<< orphan*/  SEND () ; 
 int /*<<< orphan*/  SOCKET_PROTOCOL_TCP ; 
 int /*<<< orphan*/  WRITE () ; 
 int atoi (char*) ; 
 int cmd ; 
 int cmd_size ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 void* frame_offset ; 
 int /*<<< orphan*/  frame_offset_cmd (int) ; 
 int getopt_long (int,char**,char*,struct option const*,int /*<<< orphan*/ *) ; 
 scalar_t__ htonl (int) ; 
 scalar_t__* malloc (int) ; 
 void* ntohl (scalar_t__) ; 
 int open (char const*,int,...) ; 
 char* optarg ; 
 int optind ; 
 scalar_t__* payload ; 
 int payload_size ; 
 int /*<<< orphan*/  perror (char const*) ; 
 int ranp_in ; 
 int ranp_out ; 
 int /*<<< orphan*/  send_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock ; 
 int /*<<< orphan*/  socket_close (int /*<<< orphan*/ ) ; 
 scalar_t__ socket_connect (int /*<<< orphan*/ ,struct addrinfo*,int) ; 
 int /*<<< orphan*/  socket_init (void**,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_receive_all_blocking (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  socket_send_all_blocking (int /*<<< orphan*/ ,scalar_t__*,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char **argv)
{
   struct addrinfo *addr;
   uint32_t rd_frame = 0;
   int ahead = 0;
   const char *host = "localhost",
      *ranp_in_file_name = NULL,
      *ranp_out_file_name = NULL;
   int port = RARCH_DEFAULT_PORT;
   bool playing = false, playing_started = false,
      recording = false, recording_started = false;
   const char *optstring = NULL;

   const struct option opt[] = {
      {"host",       1, NULL, 'H'},
      {"port",       1, NULL, 'P'},
      {"play",       1, NULL, 'p'},
      {"record",     1, NULL, 'r'},
      {"ahead",      1, NULL, 'a'}
   };

   while (1)
   {
      int c;

      c = getopt_long(argc, argv, "H:P:p:r:a:", opt, NULL);
      if (c == -1)
         break;

      switch (c)
      {
         case 'H':
            host = optarg;
            break;

         case 'P':
            port = atoi(optarg);
            break;

         case 'p':
            playing = true;
            ranp_in_file_name = optarg;
            break;

         case 'r':
            recording = true;
            ranp_out_file_name = optarg;
            break;

         case 'a':
            ahead = atoi(optarg);
            break;

         default:
            usage();
            return 1;
      }
   }

   if (!playing && optind < argc)
   {
      playing = true;
      ranp_in_file_name = argv[optind++];
   }
   if (!playing && !recording)
   {
      usage();
      return 1;
   }

   /* Allocate space for the protocol */
   payload_size = 4096;
   payload = malloc(payload_size);
   if (!payload)
   {
      perror("malloc");
      return 1;
   }

   /* Open the input file, if applicable */
   if (playing)
   {
      ranp_in = open(ranp_in_file_name, O_RDONLY);
      if (ranp_in == -1)
      {
         perror(ranp_in_file_name);
         return 1;
      }
   }

   /* Open the output file, if applicable */
   if (recording)
   {
      ranp_out = open(ranp_out_file_name, O_WRONLY|O_CREAT|O_EXCL, 0666);
      if (ranp_out == -1)
      {
         perror(ranp_out_file_name);
         return 1;
      }
   }

   /* Connect to the netplay server */
   if ((sock = socket_init((void **) &addr, port, host, SOCKET_PROTOCOL_TCP)) < 0)
   {
      perror("socket");
      return 1;
   }

   if (socket_connect(sock, addr, false) < 0)
   {
      perror("connect");
      return 1;
   }

   /* Expect the header */
   if (!socket_receive_all_blocking(sock, payload, 6*sizeof(uint32_t)))
   {
      fprintf(stderr, "Failed to receive connection header.\n");
      return 1;
   }

   /* If it needs a password, too bad! */
   if (payload[3])
   {
      fprintf(stderr, "Password required but unsupported.\n");
      return 1;
   }

   /* Echo the connection header back */
   socket_send_all_blocking(sock, payload, 6*sizeof(uint32_t), true);

   /* Send a nickname */
   cmd = NETPLAY_CMD_NICK;
   cmd_size = 32;
   strcpy((char *) payload, "RANetplayer");
   SEND();

   /* Receive (and ignore) the nickname */
   RECV();

   /* Receive INFO */
   RECV();
   if (cmd != NETPLAY_CMD_INFO)
   {
      fprintf(stderr, "Failed to receive INFO.");
      return 1;
   }

   /* Save the INFO */
   if (recording)
      WRITE();

   /* Echo the INFO */
   SEND();

   /* Receive SYNC */
   RECV();

   /* If we're recording and NOT playing, we start immediately in spectator
    * mode */
   if (recording && !playing)
   {
      recording_started = true;
      frame_offset = ntohl(payload[0]);
   }

   /* If we're playing, request to enter PLAY mode */
   if (playing)
   {
      cmd = NETPLAY_CMD_PLAY;
      cmd_size = sizeof(uint32_t);
      payload[0] = htonl(1);
      SEND();
   }

   /* Now handle netplay commands */
   while (1)
   {
      RECV();

      frame_offset_cmd(true);

      /* Record this command */
      if (recording && recording_started)
         WRITE();

      /* Now handle it for sync and playback */
      switch (cmd)
      {
         case NETPLAY_CMD_MODE:
            if (playing && !playing_started)
            {
               uint32_t player;

               if (cmd_size < 2*sizeof(uint32_t)) break;

               /* See if this is us joining */
               player = ntohl(payload[1]);
               if ((player & NETPLAY_CMD_MODE_BIT_PLAYING) &&
                   (player & NETPLAY_CMD_MODE_BIT_YOU))
               {
                  /* This is where we start! */
                  playing_started = true;
                  frame_offset_cmd(false);
                  frame_offset = ntohl(payload[0]);

                  if (recording)
                     recording_started = true;

                  /* Send our current input */
                  send_input(0);
               }
            }
            break;

         case NETPLAY_CMD_INPUT:
         case NETPLAY_CMD_NOINPUT:
         {
            uint32_t frame;

            if (!playing || !playing_started) break;
            if (cmd_size < sizeof(uint32_t)) break;

            frame = ntohl(payload[0]);

            /* Only sync based on server time */
            if (cmd == NETPLAY_CMD_INPUT &&
                (cmd_size < 2*sizeof(uint32_t) ||
                 (ntohl(payload[1]) != 0)))
            {
               break;
            }

            if (frame > rd_frame)
            {
               rd_frame = frame;
               if (ahead >= 0 || frame >= (uint32_t) -ahead)
               {
                  if (!send_input(frame + ahead))
                  {
                     if (!recording)
                        socket_close(sock);
                     playing = playing_started = false;
                  }
               }
            }

            break;
         }
      }
   }

   return 0;
}