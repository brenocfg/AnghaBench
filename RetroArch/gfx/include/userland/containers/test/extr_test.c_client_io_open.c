#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct VC_CONTAINER_IO_MODULE_T {int dummy; } ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_4__ {int /*<<< orphan*/  size; int /*<<< orphan*/  pf_seek; int /*<<< orphan*/  pf_read; int /*<<< orphan*/  pf_close; struct VC_CONTAINER_IO_MODULE_T* module; } ;
typedef  TYPE_1__ VC_CONTAINER_IO_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_IO_CAPABILITIES_T ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_URI_OPEN_FAILED ; 
 int /*<<< orphan*/  VC_CONTAINER_IO_CAPS_NO_CACHING ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  client_io_close ; 
 int /*<<< orphan*/  client_io_read ; 
 int /*<<< orphan*/  client_io_seek ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftell (int /*<<< orphan*/ *) ; 
 TYPE_1__* vc_container_io_create (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static VC_CONTAINER_IO_T *client_io_open( const char *psz_uri, VC_CONTAINER_STATUS_T *status )
{
   VC_CONTAINER_IO_T *p_io;
   VC_CONTAINER_IO_CAPABILITIES_T capabilities = VC_CONTAINER_IO_CAPS_NO_CACHING;
   FILE *fd;

   fd = fopen(psz_uri, "rb");
   if (!fd)
   {
      *status = VC_CONTAINER_ERROR_URI_OPEN_FAILED;
      return NULL;
   }

   p_io = vc_container_io_create( psz_uri, 0, capabilities, status );
   if(!p_io)
   {
     LOG_ERROR(0, "error creating io (%i)", *status);
     fclose(fd);
     return NULL;
   }

   p_io->module = (struct VC_CONTAINER_IO_MODULE_T *)fd;
   p_io->pf_close = client_io_close;
   p_io->pf_read = client_io_read;
   p_io->pf_seek = client_io_seek;

   //FIXME: no large file support
   fseek(fd, 0, SEEK_END);
   p_io->size = ftell(fd);
   fseek(fd, 0, SEEK_SET);

   *status = VC_CONTAINER_SUCCESS;
   return p_io;
}