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
typedef  int /*<<< orphan*/  uLongf ;
typedef  int /*<<< orphan*/  uLong ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 int /*<<< orphan*/  Z_DEFAULT_COMPRESSION ; 
 int compress2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int compress (Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen)
{
   return compress2(dest, destLen, source, sourceLen, Z_DEFAULT_COMPRESSION);
}