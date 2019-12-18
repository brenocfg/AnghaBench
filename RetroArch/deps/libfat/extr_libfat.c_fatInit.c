#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {char* name; int /*<<< orphan*/ * (* getInterface ) () ;} ;
struct TYPE_3__ {scalar_t__ argvMagic; int argc; char** argv; } ;
typedef  int /*<<< orphan*/  DISC_INTERFACE ;

/* Variables and functions */
 scalar_t__ ARGV_MAGIC ; 
 int /*<<< orphan*/  DEFAULT_SECTORS_PAGE ; 
 int PATH_MAX ; 
 TYPE_2__* _FAT_disc_interfaces ; 
 TYPE_1__* __system_argv ; 
 int /*<<< orphan*/  chdir (char*) ; 
 scalar_t__ fatMount (char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/ * stub1 () ; 

bool fatInit (uint32_t cacheSize, bool setAsDefaultDevice)
{
	int i;
	int defaultDevice = -1;
	const DISC_INTERFACE *disc;

	for (i = 0;
		_FAT_disc_interfaces[i].name != NULL && _FAT_disc_interfaces[i].getInterface != NULL;
		i++)
	{
		disc = _FAT_disc_interfaces[i].getInterface();
		if (!disc)
			continue;

      if (fatMount (_FAT_disc_interfaces[i].name, disc, 0, cacheSize, DEFAULT_SECTORS_PAGE))
      {
         /* The first device to successfully mount is set as the default */
         if (defaultDevice < 0)
            defaultDevice = i;
      }
	}

   /* None of our devices mounted */
	if (defaultDevice < 0)
		return false;

	if (setAsDefaultDevice)
   {
      char filePath[PATH_MAX];
      strcpy (filePath, _FAT_disc_interfaces[defaultDevice].name);
      strcat (filePath, ":/");
//ARGV_MAGIC means something else on wiiu
#if defined(ARGV_MAGIC) && !defined(WIIU)
      if ( __system_argv->argvMagic == ARGV_MAGIC && __system_argv->argc >= 1 && strrchr( __system_argv->argv[0], '/' )!=NULL )
      {
         /* Check the app's path against each of our mounted devices, to see
          * if we can support it. If so, change to that path. */
         for (i = 0;
               _FAT_disc_interfaces[i].name != NULL && _FAT_disc_interfaces[i].getInterface != NULL;
               i++)
         {
            if ( !strncasecmp( __system_argv->argv[0], _FAT_disc_interfaces[i].name,
                     strlen(_FAT_disc_interfaces[i].name)))
            {
               char *lastSlash;
               strcpy(filePath, __system_argv->argv[0]);
               lastSlash = strrchr( filePath, '/' );

               if ( NULL != lastSlash)
               {
                  if ( *(lastSlash - 1) == ':')
                     lastSlash++;
                  *lastSlash = 0;
               }
            }
         }
      }
#endif
      chdir (filePath);
   }

	return true;
}