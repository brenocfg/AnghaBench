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
struct TYPE_3__ {size_t width; size_t pixsize; int client; int height; scalar_t__ screen; } ;
typedef  TYPE_1__ gfx_ctx_osmesa_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 int send (int,scalar_t__,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void osmesa_fifo_write(gfx_ctx_osmesa_data_t *osmesa)
{
   int i;
   size_t len = osmesa->width * osmesa->pixsize;

   if (osmesa->client < 0)
      return;

   for (i = osmesa->height -1; i >= 0; --i)
   {
      int res = send(osmesa->client, osmesa->screen + i * len, len, MSG_NOSIGNAL);

      if (res < 0)
      {
         fprintf(stderr, "[osmesa] Lost connection to %i: %s\n", osmesa->client, strerror(errno));
         close(osmesa->client);
         osmesa->client = -1;
         break;
      }
   }
}