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
typedef  int /*<<< orphan*/ * VC_CONTAINER_READER_OPEN_FUNC_T ;

/* Variables and functions */
 char* DL_PATH_PREFIX ; 
 char* DL_PREFIX_RD ; 
 char* DL_PREFIX_WR ; 
 char const* DL_SUFFIX ; 
 unsigned int MAX (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  VCOS_DL_NOW ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (unsigned int) ; 
 int /*<<< orphan*/  snprintf (char*,unsigned int,char*,char const*,char const*,char const*,...) ; 
 unsigned int strlen (char const*) ; 
 int /*<<< orphan*/  vc_container_assert (int) ; 
 int /*<<< orphan*/  vcos_dlclose (void*) ; 
 void* vcos_dlopen (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ vcos_dlsym (void*,char const*) ; 

__attribute__((used)) static VC_CONTAINER_READER_OPEN_FUNC_T load_library(void **handle, const char *name, const char *ext, int read)
{
   #define DL_PREFIX_RD "reader_"
   #define DL_PREFIX_WR "writer_"
   const char *entrypt_read = {"reader_open"};
   const char *entrypt_write = {"writer_open"};
   char *dl_name, *entrypt_name;
   void *dl_handle;
   VC_CONTAINER_READER_OPEN_FUNC_T func = NULL;
   unsigned dl_size, ep_size, name_len = strlen(name) + (ext ? strlen(ext) : 0);

   vc_container_assert(read == 0 || read == 1);

   dl_size = strlen(DL_PATH_PREFIX) + MAX(strlen(DL_PREFIX_RD), strlen(DL_PREFIX_WR)) + name_len + strlen(DL_SUFFIX) + 1;
   if ((dl_name = malloc(dl_size)) == NULL)
      return NULL;

   ep_size = name_len + 1 + MAX(strlen(entrypt_read), strlen(entrypt_write)) + 1;
   if ((entrypt_name = malloc(ep_size)) == NULL)
   {
      free(dl_name);
      return NULL;
   }

   snprintf(dl_name, dl_size, "%s%s%s%s%s", DL_PATH_PREFIX, read ? DL_PREFIX_RD : DL_PREFIX_WR, ext ? ext : "", name, DL_SUFFIX);
   snprintf(entrypt_name, ep_size, "%s_%s%s", name, ext ? ext : "", read ? entrypt_read : entrypt_write);

   if ( (dl_handle = vcos_dlopen(dl_name, VCOS_DL_NOW)) != NULL )
   {
      /* Try generic entrypoint name before the mangled, full name */
      func = (VC_CONTAINER_READER_OPEN_FUNC_T)vcos_dlsym(dl_handle, read ? entrypt_read : entrypt_write);
#if !defined(__VIDEOCORE__) /* The following would be pointless on MW/VideoCore */
      if (!func) func = (VC_CONTAINER_READER_OPEN_FUNC_T)vcos_dlsym(dl_handle, entrypt_name);
#endif
      /* Only return handle if symbol found */
      if (func)
         *handle = dl_handle;
      else
         vcos_dlclose(dl_handle);
   }

   free(entrypt_name);
   free(dl_name);
   return func;
}