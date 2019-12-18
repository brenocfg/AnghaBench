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

/* Variables and functions */
 char* apr_cvt (double,int,int*,int*,int,char*) ; 

__attribute__((used)) static char *apr_ecvt(double arg, int ndigits, int *decpt, int *sign, char *buf)
{
    return (apr_cvt(arg, ndigits, decpt, sign, 1, buf));
}