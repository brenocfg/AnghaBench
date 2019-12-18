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
 int FALSE ; 
 int _L ; 
 int _N ; 
 int _P ; 
 int _S ; 
 int _U ; 
 int _X ; 
 int* ascii ; 

int Curl_isgraph(int c)
{
  if((c < 0) || (c >= 0x80) || (c == ' '))
    return FALSE;
  return (ascii[c] & (_N|_X|_U|_L|_P|_S));
}