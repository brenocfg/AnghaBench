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
struct stoken {size_t length; int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 char* namecopy ; 

char *
copy_name (struct stoken token)
{
  memcpy (namecopy, token.ptr, token.length);
  namecopy[token.length] = 0;
  return namecopy;
}