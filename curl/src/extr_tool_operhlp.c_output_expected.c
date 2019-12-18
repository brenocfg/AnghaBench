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
 int TRUE ; 
 scalar_t__ checkprefix (char*,char const*) ; 

bool output_expected(const char *url, const char *uploadfile)
{
  if(!uploadfile)
    return TRUE;  /* download */
  if(checkprefix("http://", url) || checkprefix("https://", url))
    return TRUE;   /* HTTP(S) upload */

  return FALSE; /* non-HTTP upload, probably no output should be expected */
}