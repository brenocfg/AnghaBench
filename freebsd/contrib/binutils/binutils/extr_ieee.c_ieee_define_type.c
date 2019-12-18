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
struct ieee_buflist {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  ieee_define_named_type (struct ieee_handle*,char const*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee_buflist*) ; 

__attribute__((used)) static bfd_boolean
ieee_define_type (struct ieee_handle *info, unsigned int size,
		  bfd_boolean unsignedp, bfd_boolean localp)
{
  return ieee_define_named_type (info, (const char *) NULL,
				 (unsigned int) -1, size, unsignedp,
				 localp, (struct ieee_buflist *) NULL);
}