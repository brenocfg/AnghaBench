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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct node_t {scalar_t__ count; int bits; int weight; int m_weight; int m_bits; int numbits; struct node_t* parent; } ;
struct huffman_decoder {int numcodes; scalar_t__* datahisto; struct node_t* huffnode; } ;
typedef  int /*<<< orphan*/  list ;

/* Variables and functions */
 int MAX (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (struct node_t**) ; 
 int /*<<< orphan*/  huffman_tree_node_compare ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memmove (struct node_t**,struct node_t**,int) ; 
 int /*<<< orphan*/  memset (struct node_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qsort (struct node_t**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int huffman_build_tree(struct huffman_decoder* decoder, uint32_t totaldata, uint32_t totalweight)
{
   int nextalloc;
	int maxbits = 0;
	/* make a list of all non-zero nodes */
	struct node_t** list   = (struct node_t**)
      malloc(sizeof(struct node_t*) * decoder->numcodes * 2);
	int curcode, listitems = 0;

	memset(decoder->huffnode, 0,
         decoder->numcodes * sizeof(decoder->huffnode[0]));

	for (curcode = 0; curcode < decoder->numcodes; curcode++)
		if (decoder->datahisto[curcode] != 0)
		{
			list[listitems++] = &decoder->huffnode[curcode];
			decoder->huffnode[curcode].count = decoder->datahisto[curcode];
			decoder->huffnode[curcode].bits = curcode;

			/* scale the weight by the current effective length, ensuring we don't go to 0 */
			decoder->huffnode[curcode].weight = ((uint64_t)decoder->datahisto[curcode]) * ((uint64_t)totalweight) / ((uint64_t)totaldata);
			if (decoder->huffnode[curcode].weight == 0)
				decoder->huffnode[curcode].weight = 1;
		}

#if 0
   {
      unsigned i;
      fprintf(stderr, "Pre-sort:\n");
      for (i = 0; i < listitems; i++)
         fprintf(stderr, "weight: %d code: %d\n",
               list[i]->m_weight, list[i]->m_bits);
   }
#endif

	/* sort the list by weight, largest weight first */
	qsort(&list[0], listitems, sizeof(list[0]), huffman_tree_node_compare);

#if 0
   fprintf(stderr, "Post-sort:\n");
   for (int i = 0; i < listitems; i++) {
      fprintf(stderr, "weight: %d code: %d\n", list[i]->m_weight, list[i]->m_bits);
   }
   fprintf(stderr, "===================\n");
#endif

	/* now build the tree */
	nextalloc = decoder->numcodes;

	while (listitems > 1)
	{
		int curitem;
		/* remove lowest two items */
		struct node_t* node1   = &(*list[--listitems]);
		struct node_t* node0   = &(*list[--listitems]);

		/* create new node */
		struct node_t* newnode = &decoder->huffnode[nextalloc++];
		newnode->parent        = NULL;
		node0->parent          =
         node1->parent       = newnode;
		newnode->weight        =
         node0->weight + node1->weight;

		/* insert into list at appropriate location */
		for (curitem = 0; curitem < listitems; curitem++)
			if (newnode->weight > list[curitem]->weight)
			{
				memmove(&list[curitem+1],
                  &list[curitem],
                  (listitems - curitem) * sizeof(list[0]));
				break;
			}
		list[curitem] = newnode;
		listitems++;
	}

	/* compute the number of bits in each code,
    * and fill in another histogram */
	for (curcode = 0; curcode < decoder->numcodes; curcode++)
	{
		struct node_t *curnode;
		struct node_t* node = &decoder->huffnode[curcode];
		node->numbits = 0;
		node->bits = 0;

		/* if we have a non-zero weight, compute the number of bits */
		if (node->weight > 0)
		{
			/* determine the number of bits for this node */
			for (curnode = node;
               curnode->parent != NULL; curnode = curnode->parent)
				node->numbits++;
			if (node->numbits == 0)
				node->numbits = 1;

			/* keep track of the max */
			maxbits = MAX(maxbits, ((int)node->numbits));
		}
	}
   free(list);
	return maxbits;
}