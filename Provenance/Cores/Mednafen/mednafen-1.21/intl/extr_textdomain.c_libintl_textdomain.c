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
 char* _nl_current_default_domain ; 
 char* _nl_default_default_domain ; 
 int /*<<< orphan*/  _nl_msg_cat_cntr ; 
 int /*<<< orphan*/  _nl_state_lock ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  gl_rwlock_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_rwlock_wrlock (int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strdup (char const*) ; 
 int strlen (char const*) ; 

char *
TEXTDOMAIN (const char *domainname)
{
  char *new_domain;
  char *old_domain;

  /* A NULL pointer requests the current setting.  */
  if (domainname == NULL)
    return (char *) _nl_current_default_domain;

  gl_rwlock_wrlock (_nl_state_lock);

  old_domain = (char *) _nl_current_default_domain;

  /* If domain name is the null string set to default domain "messages".  */
  if (domainname[0] == '\0'
      || strcmp (domainname, _nl_default_default_domain) == 0)
    {
      _nl_current_default_domain = _nl_default_default_domain;
      new_domain = (char *) _nl_current_default_domain;
    }
  else if (strcmp (domainname, old_domain) == 0)
    /* This can happen and people will use it to signal that some
       environment variable changed.  */
    new_domain = old_domain;
  else
    {
      /* If the following malloc fails `_nl_current_default_domain'
	 will be NULL.  This value will be returned and so signals we
	 are out of core.  */
#if defined _LIBC || defined HAVE_STRDUP
      new_domain = strdup (domainname);
#else
      size_t len = strlen (domainname) + 1;
      new_domain = (char *) malloc (len);
      if (new_domain != NULL)
	memcpy (new_domain, domainname, len);
#endif

      if (new_domain != NULL)
	_nl_current_default_domain = new_domain;
    }

  /* We use this possibility to signal a change of the loaded catalogs
     since this is most likely the case and there is no other easy we
     to do it.  Do it only when the call was successful.  */
  if (new_domain != NULL)
    {
      ++_nl_msg_cat_cntr;

      if (old_domain != new_domain && old_domain != _nl_default_default_domain)
	free (old_domain);
    }

  gl_rwlock_unlock (_nl_state_lock);

  return new_domain;
}