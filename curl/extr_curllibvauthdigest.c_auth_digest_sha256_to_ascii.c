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
 int /*<<< orphan*/  msnprintf (char*,int,char*,unsigned char) ; 

__attribute__((used)) static void auth_digest_sha256_to_ascii(unsigned char *source, /* 32 bytes */
                                     unsigned char *dest) /* 65 bytes */
{
  int i;
  for(i = 0; i < 32; i++)
    msnprintf((char *) &dest[i * 2], 3, "%02x", source[i]);
}