__attribute__((used)) static void cvm_oct_free_hw_skbuff(int pool, int size, int elements)
{
	char *memory;

	do {
		memory = cvmx_fpa_alloc(pool);
		if (memory) {
			struct sk_buff *skb =
			    *(struct sk_buff **)(memory - sizeof(void *));
			elements--;
			dev_kfree_skb(skb);
		}
	} while (memory);

	if (elements < 0)
		pr_warning("Freeing of pool %u had too many skbuffs (%d)\n",
		     pool, elements);
	else if (elements > 0)
		pr_warning("Freeing of pool %u is missing %d skbuffs\n",
		       pool, elements);
}