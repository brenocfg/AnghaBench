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
struct TYPE_2__ {size_t rem; int overflow; size_t data; } ;
typedef  TYPE_1__ CSeqOutStreamBuf ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (size_t,void const*,size_t) ; 

__attribute__((used)) static size_t MyWrite(void *pp, const void *data, size_t size)
{
  CSeqOutStreamBuf *p = (CSeqOutStreamBuf *)pp;
  if (p->rem < size)
  {
    size = p->rem;
    p->overflow = true;
  }
  memcpy(p->data, data, size);
  p->rem -= size;
  p->data += size;
  return size;
}