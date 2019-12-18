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
typedef  int ufile_ptr ;
typedef  int file_ptr ;
typedef  int bfd_vma ;

/* Variables and functions */

__attribute__((used)) static file_ptr
vma_page_aligned_bias (bfd_vma vma, ufile_ptr off, bfd_vma maxpagesize)
{
  return ((vma - off) % maxpagesize);
}