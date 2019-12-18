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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  CSzData ;

/* Variables and functions */
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_OK ; 
 int /*<<< orphan*/  SzReaduint8_t (int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static SRes SzReaduint32_t(CSzData *sd, uint32_t *value)
{
   int i;
   *value = 0;
   for (i = 0; i < 4; i++)
   {
      uint8_t b;
      RINOK(SzReaduint8_t(sd, &b));
      *value |= ((uint32_t)(b) << (8 * i));
   }
   return SZ_OK;
}