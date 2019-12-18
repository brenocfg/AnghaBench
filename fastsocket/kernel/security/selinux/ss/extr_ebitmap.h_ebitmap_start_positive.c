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
struct ebitmap_node {unsigned int startbit; int /*<<< orphan*/  maps; struct ebitmap_node* next; } ;
struct ebitmap {struct ebitmap_node* node; } ;

/* Variables and functions */
 unsigned int EBITMAP_SIZE ; 
 unsigned int ebitmap_length (struct ebitmap*) ; 
 unsigned int find_first_bit (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline unsigned int ebitmap_start_positive(struct ebitmap *e,
						  struct ebitmap_node **n)
{
	unsigned int ofs;

	for (*n = e->node; *n; *n = (*n)->next) {
		ofs = find_first_bit((*n)->maps, EBITMAP_SIZE);
		if (ofs < EBITMAP_SIZE)
			return (*n)->startbit + ofs;
	}
	return ebitmap_length(e);
}