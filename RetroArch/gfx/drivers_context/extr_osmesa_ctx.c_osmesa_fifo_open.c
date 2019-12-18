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
struct sockaddr_un {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct TYPE_3__ {scalar_t__ socket; int client; int width; int height; int pixsize; } ;
typedef  TYPE_1__ gfx_ctx_osmesa_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ bind (scalar_t__,struct sockaddr_un*,int) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* g_osmesa_fifo ; 
 scalar_t__ listen (scalar_t__,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void osmesa_fifo_open(gfx_ctx_osmesa_data_t *osmesa)
{
   struct sockaddr_un saun, fsaun;

   osmesa->socket = socket(AF_UNIX, SOCK_STREAM, 0);
   osmesa->client = -1;

   if (osmesa->socket < 0)
   {
      perror("[osmesa] socket()");
      return;
   }

   saun.sun_family = AF_UNIX;

   strlcpy(saun.sun_path, g_osmesa_fifo, sizeof(saun.sun_path));

   unlink(g_osmesa_fifo);

   if (bind(osmesa->socket, &saun, sizeof(saun.sun_family) + sizeof(saun.sun_path)) < 0)
   {
      perror("[osmesa] bind()");
      close(osmesa->socket);
      return;
   }

   if (listen(osmesa->socket, 1) < 0)
   {
      perror("[osmesa] listen()");
      close(osmesa->socket);
      return;
   }

   fprintf(stderr, "[osmesa] Frame size is %ix%ix%i\n", osmesa->width, osmesa->height, osmesa->pixsize);
   fprintf(stderr, "[osmesa] Please connect to unix:%s\n", g_osmesa_fifo);
}