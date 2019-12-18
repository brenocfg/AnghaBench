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
struct snd_trident {int dummy; } ;

/* Variables and functions */
 int ALIGN_PAGE_SIZE ; 
 int /*<<< orphan*/  get_aligned_page (int) ; 
 char* page_to_ptr (struct snd_trident*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *offset_ptr(struct snd_trident *trident, int offset)
{
	char *ptr;
	ptr = page_to_ptr(trident, get_aligned_page(offset));
	ptr += offset % ALIGN_PAGE_SIZE;
	return (void*)ptr;
}