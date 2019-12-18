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
typedef  int u_int8_t ;

/* Variables and functions */
#define  CES_CODE_SET_ASCII 130 
#define  CES_CODE_SET_BINARY 129 
#define  CES_CODE_SET_UTF_8 128 
 int /*<<< orphan*/  CODESET ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  UTF8CODESET ; 
 char* nl_langinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_designator(const char *designator, u_int8_t code_set,
    u_int8_t designator_length)
{
	printf(" serial number: <");
	switch (code_set) {
	case CES_CODE_SET_ASCII: {
		/*
		 * The driver insures that the string is always NUL terminated.
		 */
		printf("%s", designator);
		break;
	}
	case CES_CODE_SET_UTF_8: {
		char *cs_native;

		setlocale(LC_ALL, "");
		cs_native = nl_langinfo(CODESET);

		/* See if we can natively print UTF-8 */
		if (strcmp(cs_native, UTF8CODESET) == 0)
			cs_native = NULL;

		if (cs_native == NULL) {
			/* We can natively print UTF-8, so use printf. */
			printf("%s", designator);
		} else {
			int i;

			/*
			 * We can't natively print UTF-8.  We should
			 * convert it to the terminal's codeset, but that
			 * requires iconv(3) and FreeBSD doesn't have
			 * iconv(3) in the base system yet.  So we use %XX
			 * notation for non US-ASCII characters instead.
			 */
			for (i = 0; i < designator_length &&
			    designator[i] != '\0'; i++) {
				if ((unsigned char)designator[i] < 0x80)
					printf("%c", designator[i]);
				else
					printf("%%%02x",
					    (unsigned char)designator[i]);
			}
		}
		break;
	}
	case CES_CODE_SET_BINARY: {
		int i;

		for (i = 0; i < designator_length; i++)
			printf("%02X%s", designator[i],
			    (i == designator_length - 1) ? "" : " ");
		break;
	}
	default:
		break;
	}
	printf(">");
}