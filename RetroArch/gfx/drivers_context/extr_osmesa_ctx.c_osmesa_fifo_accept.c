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
struct pollfd {int /*<<< orphan*/  events; int /*<<< orphan*/  fd; } ;
struct TYPE_3__ {scalar_t__ client; int /*<<< orphan*/  socket; } ;
typedef  TYPE_1__ gfx_ctx_osmesa_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 scalar_t__ accept (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int poll (struct pollfd*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void osmesa_fifo_accept(gfx_ctx_osmesa_data_t *osmesa)
{
   int res;
   struct pollfd fds;
   fds.fd = osmesa->socket;
   fds.events = POLLIN;

   if (osmesa->client >= 0)
      return;

   res = poll(&fds, 1, 0);

   if (res < 0)
      perror("[osmesa] poll() error");
   else if (res > 0)
   {
      osmesa->client = accept(osmesa->socket, NULL, NULL);
      fprintf(stderr, "[osmesa] Client %i connected.\n", osmesa->client);
   }
}