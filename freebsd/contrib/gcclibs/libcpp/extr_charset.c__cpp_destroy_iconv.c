#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ func; int /*<<< orphan*/  cd; } ;
struct TYPE_5__ {scalar_t__ func; int /*<<< orphan*/  cd; } ;
struct TYPE_7__ {TYPE_2__ wide_cset_desc; TYPE_1__ narrow_cset_desc; } ;
typedef  TYPE_3__ cpp_reader ;

/* Variables and functions */
 scalar_t__ HAVE_ICONV ; 
 scalar_t__ convert_using_iconv ; 
 int /*<<< orphan*/  iconv_close (int /*<<< orphan*/ ) ; 

void
_cpp_destroy_iconv (cpp_reader *pfile)
{
  if (HAVE_ICONV)
    {
      if (pfile->narrow_cset_desc.func == convert_using_iconv)
	iconv_close (pfile->narrow_cset_desc.cd);
      if (pfile->wide_cset_desc.func == convert_using_iconv)
	iconv_close (pfile->wide_cset_desc.cd);
    }
}