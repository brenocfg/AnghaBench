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
typedef  unsigned int uint32_t ;

/* Variables and functions */
 int LZ4_COMPRESS_HASH_BITS ; 

__attribute__((used)) static inline uint32_t lz4_hash(uint32_t x) { return (x * 2654435761U) >> (32 - LZ4_COMPRESS_HASH_BITS); }