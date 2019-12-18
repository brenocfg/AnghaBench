#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pos; scalar_t__ buf; } ;
typedef  TYPE_1__ SStringBuilder ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,size_t) ; 
 int /*<<< orphan*/  taosStringBuilderEnsureCapacity (TYPE_1__*,size_t) ; 

void taosStringBuilderAppend(SStringBuilder* sb, const void* data, size_t len) {
  taosStringBuilderEnsureCapacity(sb, len);
  memcpy(sb->buf + sb->pos, data, len);
  sb->pos += len;
}