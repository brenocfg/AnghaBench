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
typedef  scalar_t__ uLong ;
typedef  scalar_t__ uInt ;

/* Variables and functions */
 unsigned char const* Z_NULL ; 
 scalar_t__ crc32 (scalar_t__,unsigned char const*,scalar_t__) ; 
 int /*<<< orphan*/  fwrite (unsigned char const*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_uLong (scalar_t__) ; 
 int /*<<< orphan*/  stdout ; 

void
put_chunk(const unsigned char *chunk, uInt length)
{
   uLong crc;

   put_uLong(length-4); /* Exclude the tag */

   fwrite(chunk, length, 1, stdout);

   crc = crc32(0, Z_NULL, 0);
   put_uLong(crc32(crc, chunk, length));
}