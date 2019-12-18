char *string(char *str) {
	static struct string { struct string *link; char str[1]; } *list;
	struct string *p;

	for (p = list; p; p = p->link)
		if (strcmp(p->str, str) == 0)
			return p->str;
	p = (struct string *)alloc(strlen(str) + sizeof *p);
	strcpy(p->str, str);
	p->link = list;
	list = p;
	return p->str;
}