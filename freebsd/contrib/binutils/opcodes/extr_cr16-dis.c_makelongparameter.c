#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nbits; scalar_t__ val; } ;
typedef  TYPE_1__ parameter ;
typedef  scalar_t__ dwordU ;
typedef  int /*<<< orphan*/  ULONGLONG ;

/* Variables and functions */
 scalar_t__ EXTRACT (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static parameter
makelongparameter (ULONGLONG val, int start, int end)
{
  parameter p;

  p.val = (dwordU) EXTRACT (val, 48 - end, end - start);
  p.nbits = end - start;
  return p;
}