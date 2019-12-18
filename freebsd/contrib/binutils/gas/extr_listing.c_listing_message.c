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
struct TYPE_3__ {char* message; } ;
typedef  TYPE_1__ list_info_type ;

/* Variables and functions */
 TYPE_1__* listing_tail ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ xmalloc (unsigned int) ; 

__attribute__((used)) static void
listing_message (const char *name, const char *message)
{
  if (listing_tail != (list_info_type *) NULL)
    {
      unsigned int l = strlen (name) + strlen (message) + 1;
      char *n = (char *) xmalloc (l);
      strcpy (n, name);
      strcat (n, message);
      listing_tail->message = n;
    }
}