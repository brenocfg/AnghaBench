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
typedef  int /*<<< orphan*/  y ;
typedef  int /*<<< orphan*/  x ;
struct tiny {int c; } ;

/* Variables and functions */
 int /*<<< orphan*/  f (int,struct tiny,struct tiny,struct tiny) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

void b ()
{
  struct tiny x[3];
  struct tiny y;
  printf("sizeof tiny: %d (3 of them: %d)\n", sizeof(y), sizeof(x));
  x[0].c = 10;
  x[1].c = 11;
  x[2].c = 12;
  f (3, x[0], x[1], x[2]);
}