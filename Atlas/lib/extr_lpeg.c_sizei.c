#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ code; int offset; } ;
struct TYPE_6__ {TYPE_1__ i; } ;
typedef  TYPE_2__ Instruction ;

/* Variables and functions */
 int CHARSETINSTSIZE ; 
 scalar_t__ IFunc ; 
 scalar_t__ hascharset (TYPE_2__ const*) ; 

__attribute__((used)) static int sizei (const Instruction *i) {
  if (hascharset(i)) return CHARSETINSTSIZE;
  else if (i->i.code == IFunc) return i->i.offset;
  else return 1;
}