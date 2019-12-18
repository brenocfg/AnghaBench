h2() {
	char *b; const void *p;
	p = b;
	b = p;		/* error */
}