#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  snd_seq_t ;
typedef  int /*<<< orphan*/  snd_seq_port_info_t ;
typedef  int /*<<< orphan*/  snd_seq_client_info_t ;
struct TYPE_3__ {int client; int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ snd_seq_addr_t ;

/* Variables and functions */
 unsigned int SND_SEQ_PORT_TYPE_MIDI_GENERIC ; 
 int /*<<< orphan*/  snd_seq_client_info_alloca (int /*<<< orphan*/ **) ; 
 int snd_seq_client_info_get_client (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_seq_client_info_set_client (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snd_seq_port_info_alloca (int /*<<< orphan*/ **) ; 
 unsigned int snd_seq_port_info_get_capability (int /*<<< orphan*/ *) ; 
 char* snd_seq_port_info_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_seq_port_info_get_port (int /*<<< orphan*/ *) ; 
 unsigned int snd_seq_port_info_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_seq_port_info_set_client (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snd_seq_port_info_set_port (int /*<<< orphan*/ *,int) ; 
 scalar_t__ snd_seq_query_next_client (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ snd_seq_query_next_port (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ string_is_equal (char const*,char const*) ; 

__attribute__((used)) static bool alsa_midi_get_port(snd_seq_t *seq, const char *name, unsigned caps,
      snd_seq_addr_t *addr)
{
   snd_seq_client_info_t *client_info;
   snd_seq_port_info_t *port_info;

   snd_seq_client_info_alloca(&client_info);
   snd_seq_port_info_alloca(&port_info);

   snd_seq_client_info_set_client(client_info, -1);
   while (snd_seq_query_next_client(seq, client_info) == 0)
   {
      int client_id = snd_seq_client_info_get_client(client_info);

      snd_seq_port_info_set_client(port_info, client_id);
      snd_seq_port_info_set_port(port_info, -1);

      while (snd_seq_query_next_port(seq, port_info) == 0)
      {
         unsigned port_caps = snd_seq_port_info_get_capability(port_info);
         unsigned type      = snd_seq_port_info_get_type(port_info);

         if ((type & SND_SEQ_PORT_TYPE_MIDI_GENERIC) && (port_caps & caps) == caps)
         {
            const char *port_name = snd_seq_port_info_get_name(port_info);

            if (string_is_equal(port_name, name))
            {
               addr->client = client_id;
               addr->port   = snd_seq_port_info_get_port(port_info);

               return true;
            }
         }
      }
   }

   return false;
}