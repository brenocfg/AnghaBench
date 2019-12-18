void *edac_align_ptr(void *ptr, unsigned size)
{
	unsigned align, r;

	/* Here we assume that the alignment of a "long long" is the most
	 * stringent alignment that the compiler will ever provide by default.
	 * As far as I know, this is a reasonable assumption.
	 */
	if (size > sizeof(long))
		align = sizeof(long long);
	else if (size > sizeof(int))
		align = sizeof(long);
	else if (size > sizeof(short))
		align = sizeof(int);
	else if (size > sizeof(char))
		align = sizeof(short);
	else
		return (char *)ptr;

	r = size % align;

	if (r == 0)
		return (char *)ptr;

	return (void *)(((unsigned long)ptr) + align - r);
}