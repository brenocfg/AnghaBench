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
struct TYPE_4__ {char* buf; size_t pos; } ;
typedef  TYPE_1__ SStringBuilder ;

/* Variables and functions */
 int /*<<< orphan*/  taosStringBuilderEnsureCapacity (TYPE_1__*,int) ; 

char* taosStringBuilderGetResult(SStringBuilder* sb, size_t* len) {
  taosStringBuilderEnsureCapacity(sb, 1);
  sb->buf[sb->pos] = 0;
  if (len != NULL) {
    *len = sb->pos;
  }
  return sb->buf;
}