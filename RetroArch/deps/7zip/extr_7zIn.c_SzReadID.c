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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  CSzData ;

/* Variables and functions */
 int /*<<< orphan*/  SzReadNumber (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static SRes SzReadID(CSzData *sd, uint64_t *value)
{
   return SzReadNumber(sd, value);
}