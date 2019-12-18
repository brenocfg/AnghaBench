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
 char* LIBDIR ; 
 char* LOCALEDIR ; 
 char* LOCALE_ALIAS_PATH ; 
 int MAXPATHLEN ; 
 char* _nlos2_libdir ; 
 char* _nlos2_localealiaspath ; 
 char* _nlos2_localedir ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  libintl_nl_default_dirname ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static __attribute__((constructor)) void
nlos2_initialize ()
{
  char *root = getenv ("UNIXROOT");
  char *gnulocaledir = getenv ("GNULOCALEDIR");

  _nlos2_libdir = gnulocaledir;
  if (!_nlos2_libdir)
    {
      if (root)
        {
          size_t sl = strlen (root);
          _nlos2_libdir = (char *) malloc (sl + strlen (LIBDIR) + 1);
          memcpy (_nlos2_libdir, root, sl);
          memcpy (_nlos2_libdir + sl, LIBDIR, strlen (LIBDIR) + 1);
        }
      else
        _nlos2_libdir = LIBDIR;
    }

  _nlos2_localealiaspath = gnulocaledir;
  if (!_nlos2_localealiaspath)
    {
      if (root)
        {
          size_t sl = strlen (root);
          _nlos2_localealiaspath = (char *) malloc (sl + strlen (LOCALE_ALIAS_PATH) + 1);
          memcpy (_nlos2_localealiaspath, root, sl);
          memcpy (_nlos2_localealiaspath + sl, LOCALE_ALIAS_PATH, strlen (LOCALE_ALIAS_PATH) + 1);
        }
     else
        _nlos2_localealiaspath = LOCALE_ALIAS_PATH;
    }

  _nlos2_localedir = gnulocaledir;
  if (!_nlos2_localedir)
    {
      if (root)
        {
          size_t sl = strlen (root);
          _nlos2_localedir = (char *) malloc (sl + strlen (LOCALEDIR) + 1);
          memcpy (_nlos2_localedir, root, sl);
          memcpy (_nlos2_localedir + sl, LOCALEDIR, strlen (LOCALEDIR) + 1);
        }
      else
        _nlos2_localedir = LOCALEDIR;
    }

  if (strlen (_nlos2_localedir) <= MAXPATHLEN)
    strcpy (libintl_nl_default_dirname, _nlos2_localedir);
}