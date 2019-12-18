#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* audio_device; } ;
struct TYPE_5__ {TYPE_1__ arrays; } ;
typedef  TYPE_2__ settings_t ;

/* Variables and functions */
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 
 char* strtok_r (char*,char*,char**) ; 

__attribute__((used)) static int parse_ports(char **dest_ports, const char **jports)
{
   int i;
   char           *save   = NULL;
   int           parsed   = 0;
   settings_t *settings   = config_get_ptr();
   char *audio_device_cpy = strdup(settings->arrays.audio_device);
   const char      *con   = strtok_r(audio_device_cpy, ",", &save);

   if (con)
      dest_ports[parsed++] = strdup(con);
   con = strtok_r(NULL, ",", &save);
   if (con)
      dest_ports[parsed++] = strdup(con);

   for (i = parsed; i < 2; i++)
      dest_ports[i] = strdup(jports[i]);

   free(audio_device_cpy);
   return 2;
}