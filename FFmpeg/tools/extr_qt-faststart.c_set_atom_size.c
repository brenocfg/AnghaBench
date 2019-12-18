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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WB32 (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_WB64 (unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_atom_size(unsigned char *header, uint32_t header_size, uint64_t size)
{
    switch (header_size) {
    case 8:
        AV_WB32(header, size);
        break;

    case 16:
        AV_WB64(header + 8, size);
        break;
    }
}