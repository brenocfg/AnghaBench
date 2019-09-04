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
typedef  int /*<<< orphan*/  Endianess ;

/* Variables and functions */
 int /*<<< orphan*/  BigEndian ; 
 int /*<<< orphan*/  LittleEndian ; 
 int /*<<< orphan*/  UnknwonEndian ; 

__attribute__((used)) static Endianess endianess(void)
{
  union
  {
    long l;
    char c[sizeof(long)];
  } u;

  u.l = 1;
  return (u.c[0] == 1) ? LittleEndian : ((u.c[sizeof(long) - 1] == 1) ? BigEndian : UnknwonEndian);
}