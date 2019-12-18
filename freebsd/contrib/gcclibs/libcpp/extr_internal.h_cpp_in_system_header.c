#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* buffer; } ;
typedef  TYPE_2__ cpp_reader ;
struct TYPE_4__ {int sysp; } ;

/* Variables and functions */

__attribute__((used)) static inline int
cpp_in_system_header (cpp_reader *pfile)
{
  return pfile->buffer ? pfile->buffer->sysp : 0;
}