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
typedef  int /*<<< orphan*/  rc_uint_type ;
struct TYPE_2__ {int /*<<< orphan*/  sec; int /*<<< orphan*/  abfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_fatal (char*) ; 
 int /*<<< orphan*/  bfd_set_section_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ mc_bfd ; 

__attribute__((used)) static void
set_windmc_bfd_content (const void *data, rc_uint_type off, rc_uint_type length)
{
  if (! bfd_set_section_contents (mc_bfd.abfd, mc_bfd.sec, data, off, length))
    bfd_fatal ("bfd_set_section_contents");
}