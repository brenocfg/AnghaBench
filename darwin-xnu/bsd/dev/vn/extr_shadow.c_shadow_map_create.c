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
struct TYPE_3__ {int blocks_per_band; int file_size_blocks; int zeroth_band; int block_size; void* shadow_size_bands; scalar_t__ next_band; void* bands; void* block_bitmap; } ;
typedef  TYPE_1__ shadow_map_t ;
typedef  int /*<<< orphan*/  off_t ;
typedef  void band_number_t ;

/* Variables and functions */
 int BAND_MAX ; 
 int BAND_SIZE_DEFAULT ; 
 int block_bitmap_size (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (void*,int) ; 
 void* howmany (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  my_free (void*) ; 
 void* my_malloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

shadow_map_t *
shadow_map_create(off_t file_size, off_t shadow_size, 
		  uint32_t band_size, uint32_t block_size)
{
    void *		block_bitmap = NULL;
    uint32_t		bitmap_size;
    band_number_t *	bands = NULL;
    shadow_map_t *	map;
    uint32_t		n_bands = 0;

    if (band_size == 0) {
	band_size = BAND_SIZE_DEFAULT;
    }

    n_bands = howmany(file_size, band_size);
    if (n_bands > (BAND_MAX + 1)) {
	printf("file is too big: %d > %d\n",
	       n_bands, BAND_MAX);
	goto failure;
    }

    /* create a block bitmap, one bit per block */
    bitmap_size = block_bitmap_size(file_size, block_size);
    block_bitmap = my_malloc(bitmap_size);
    if (block_bitmap == NULL) {
	printf("failed to allocate bitmap\n");
	goto failure;
    }
    bzero(block_bitmap, bitmap_size);

    /* get the band map */
    bands = (band_number_t *)my_malloc(n_bands * sizeof(band_number_t));
    if (bands == NULL) {
	printf("failed to allocate bands\n");
	goto failure;
    }
    bzero(bands, n_bands * sizeof(band_number_t));

    map = my_malloc(sizeof(*map));
    if (map == NULL) {
	printf("failed to allocate map\n");
	goto failure;
    }
    map->blocks_per_band = band_size / block_size;
    map->block_bitmap = block_bitmap;
    map->bands = bands;
    map->file_size_blocks = n_bands * map->blocks_per_band;
    map->next_band = 0;
    map->zeroth_band = -1;
    map->shadow_size_bands = howmany(shadow_size, band_size);
    map->block_size = block_size;
    return (map);
	
 failure:
    if (block_bitmap)
	my_free(block_bitmap);
    if (bands)
	my_free(bands);
    return (NULL);
}