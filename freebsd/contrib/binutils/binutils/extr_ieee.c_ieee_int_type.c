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
struct ieee_handle {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 char* _ (char*) ; 
 scalar_t__ builtin_signed_char ; 
 scalar_t__ builtin_signed_long ; 
 scalar_t__ builtin_signed_long_long ; 
 scalar_t__ builtin_signed_short_int ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  ieee_push_type (struct ieee_handle*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static bfd_boolean
ieee_int_type (void *p, unsigned int size, bfd_boolean unsignedp)
{
  struct ieee_handle *info = (struct ieee_handle *) p;
  unsigned int indx;

  switch (size)
    {
    case 1:
      indx = (int) builtin_signed_char;
      break;
    case 2:
      indx = (int) builtin_signed_short_int;
      break;
    case 4:
      indx = (int) builtin_signed_long;
      break;
    case 8:
      indx = (int) builtin_signed_long_long;
      break;
    default:
      fprintf (stderr, _("IEEE unsupported integer type size %u\n"), size);
      return FALSE;
    }

  if (unsignedp)
    ++indx;

  return ieee_push_type (info, indx, size, unsignedp, FALSE);
}