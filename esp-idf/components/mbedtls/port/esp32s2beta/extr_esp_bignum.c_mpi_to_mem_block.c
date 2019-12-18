#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {size_t n; int* p; } ;
typedef  TYPE_1__ mbedtls_mpi ;

/* Variables and functions */

__attribute__((used)) static inline void mpi_to_mem_block(uint32_t mem_base, const mbedtls_mpi *mpi, size_t num_words)
{
    uint32_t *pbase = (uint32_t *)mem_base;
    uint32_t copy_words = num_words < mpi->n ? num_words : mpi->n;

    /* Copy MPI data to memory block registers */
    for (int i = 0; i < copy_words; i++) {
        pbase[i] = mpi->p[i];
    }

    /* Zero any remaining memory block data */
    for (int i = copy_words; i < num_words; i++) {
        pbase[i] = 0;
    }

    /* Note: not executing memw here, can do it before we start a bignum operation */
}