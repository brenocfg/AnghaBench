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

/* Variables and functions */
 scalar_t__ FSGetMountSource (void*,void*,int /*<<< orphan*/ ,void*,int) ; 
 int FSMount (void*,void*,void*,char*,scalar_t__,int) ; 
 scalar_t__ FS_MAX_MOUNTPATH_SIZE ; 
 scalar_t__ FS_MOUNT_SOURCE_SIZE ; 
 int /*<<< orphan*/  FS_SOURCETYPE_EXTERNAL ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (scalar_t__) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

int MountFS(void *pClient, void *pCmd, char **mount_path)
{
   char *mountPath = NULL;
   int result      = -1;
   void *mountSrc  = malloc(FS_MOUNT_SOURCE_SIZE);

   if (!mountSrc)
      return -3;

   mountPath       = (char*) malloc(FS_MAX_MOUNTPATH_SIZE);

   if (!mountPath)
   {
      free(mountSrc);
      return -4;
   }

   memset(mountSrc, 0, FS_MOUNT_SOURCE_SIZE);
   memset(mountPath, 0, FS_MAX_MOUNTPATH_SIZE);

   /* Mount sdcard */
   if (FSGetMountSource(pClient, pCmd, FS_SOURCETYPE_EXTERNAL, mountSrc, -1) == 0)
   {
      result = FSMount(pClient, pCmd, mountSrc, mountPath, FS_MAX_MOUNTPATH_SIZE, -1);

      if ((result == 0) && mount_path)
      {
         *mount_path = (char*)malloc(strlen(mountPath) + 1);
         if (*mount_path)
            strcpy(*mount_path, mountPath);
      }
   }

   free(mountPath);
   free(mountSrc);
   return result;
}