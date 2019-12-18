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
typedef  int /*<<< orphan*/  png_byte ;

/* Variables and functions */
 int PNG_CHUNK_ANCILLARY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PNG_U32 (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

__attribute__((used)) static int
ancillaryb(const png_byte *name)
{
   return PNG_CHUNK_ANCILLARY(PNG_U32(name[0], name[1], name[2], name[3]));
}