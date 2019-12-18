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
 int /*<<< orphan*/  AV_WB24 (unsigned char*,int) ; 
 int CHUNK_HEADER_SIZE ; 

__attribute__((used)) static int write_chunk_header(unsigned char *buf, int chunk_type, int chunk_size)
{
    buf[0] = chunk_type;
    AV_WB24(&buf[1], chunk_size + CHUNK_HEADER_SIZE);
    return CHUNK_HEADER_SIZE;
}