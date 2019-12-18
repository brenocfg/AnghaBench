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
 scalar_t__ AUTO_DEMANGLING ; 
 scalar_t__ DEPRECATED_STREQN (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  GCC_PRODUCER ; 
 int /*<<< orphan*/  GNU_DEMANGLING_STYLE_STRING ; 
 int /*<<< orphan*/  GPLUS_PRODUCER ; 
 int /*<<< orphan*/  LCC_PRODUCER ; 
 int /*<<< orphan*/  LUCID_DEMANGLING_STYLE_STRING ; 
 int processing_gcc_compilation ; 
 int /*<<< orphan*/  set_demangling_style (int /*<<< orphan*/ ) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void
handle_producer (char *producer)
{

  /* If this compilation unit was compiled with g++ or gcc, then set the
     processing_gcc_compilation flag. */

  if (DEPRECATED_STREQN (producer, GCC_PRODUCER, strlen (GCC_PRODUCER)))
    {
      char version = producer[strlen (GCC_PRODUCER)];
      processing_gcc_compilation = (version == '2' ? 2 : 1);
    }
  else
    {
      processing_gcc_compilation =
	strncmp (producer, GPLUS_PRODUCER, strlen (GPLUS_PRODUCER)) == 0;
    }

  /* Select a demangling style if we can identify the producer and if
     the current style is auto.  We leave the current style alone if it
     is not auto.  We also leave the demangling style alone if we find a
     gcc (cc1) producer, as opposed to a g++ (cc1plus) producer. */

  if (AUTO_DEMANGLING)
    {
      if (DEPRECATED_STREQN (producer, GPLUS_PRODUCER, strlen (GPLUS_PRODUCER)))
	{
#if 0
	  /* For now, stay with AUTO_DEMANGLING for g++ output, as we don't
	     know whether it will use the old style or v3 mangling.  */
	  set_demangling_style (GNU_DEMANGLING_STYLE_STRING);
#endif
	}
      else if (DEPRECATED_STREQN (producer, LCC_PRODUCER, strlen (LCC_PRODUCER)))
	{
	  set_demangling_style (LUCID_DEMANGLING_STYLE_STRING);
	}
    }
}