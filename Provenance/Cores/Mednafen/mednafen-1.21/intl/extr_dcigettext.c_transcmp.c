#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  appended; } ;
struct known_translation_t {int category; int /*<<< orphan*/  encoding; int /*<<< orphan*/  localename; int /*<<< orphan*/  domainname; TYPE_1__ msgid; int /*<<< orphan*/ * domain; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
transcmp (const void *p1, const void *p2)
{
  const struct known_translation_t *s1;
  const struct known_translation_t *s2;
  int result;

  s1 = (const struct known_translation_t *) p1;
  s2 = (const struct known_translation_t *) p2;

  result = strcmp (s1->domain != NULL ? s1->msgid.appended : s1->msgid.ptr,
		   s2->domain != NULL ? s2->msgid.appended : s2->msgid.ptr);
  if (result == 0)
    {
      result = strcmp (s1->domainname, s2->domainname);
      if (result == 0)
	{
#ifdef HAVE_PER_THREAD_LOCALE
	  result = strcmp (s1->localename, s2->localename);
	  if (result == 0)
#endif
	    {
#ifdef IN_LIBGLOCALE
	      result = strcmp (s1->encoding, s2->encoding);
	      if (result == 0)
#endif
		/* We compare the category last (though this is the cheapest
		   operation) since it is hopefully always the same (namely
		   LC_MESSAGES).  */
		result = s1->category - s2->category;
	    }
	}
    }

  return result;
}