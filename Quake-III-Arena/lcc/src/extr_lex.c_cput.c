__attribute__((used)) static void *cput(int c, void *cl) {
	char *s = cl;

	if (c < 0 || c > 255)
		warning("overflow in escape sequence with resulting value `%d'\n", c);
	*s++ = c;
	return s;
}