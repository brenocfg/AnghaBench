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
struct nls_table {int dummy; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 

__attribute__((used)) static int convert_memcpy(unsigned char *output, int olen,
			  const unsigned char *input, int ilen,
			  struct nls_table *nls_from,
			  struct nls_table *nls_to)
{
	if (olen < ilen)
		return -ENAMETOOLONG;
	memcpy(output, input, ilen);
	return ilen;
}