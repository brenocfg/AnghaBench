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
typedef  int /*<<< orphan*/  wchar_t ;
struct nls_table {int (* char2uni ) (unsigned char const*,int,int /*<<< orphan*/ *) ;int (* uni2char ) (int /*<<< orphan*/ ,unsigned char*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (unsigned char const*,int,int /*<<< orphan*/ *) ; 
 int stub2 (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int write_char (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int write_unichar (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int convert_cp(unsigned char *output, int olen,
		      const unsigned char *input, int ilen,
		      struct nls_table *nls_from,
		      struct nls_table *nls_to)
{
	int len = 0;
	int n;
	wchar_t ch;

	while (ilen > 0) {
		/* convert by changing to unicode and back to the new cp */
		n = nls_from->char2uni(input, ilen, &ch);
		if (n == -EINVAL) {
			ilen--;
			n = write_char(*input++, output, olen);
			if (n < 0)
				goto fail;
			output += n;
			olen -= n;
			len += n;
			continue;
		} else if (n < 0)
			goto fail;
		input += n;
		ilen -= n;

		n = nls_to->uni2char(ch, output, olen);
		if (n == -EINVAL)
			n = write_unichar(ch, output, olen);
		if (n < 0)
			goto fail;
		output += n;
		olen -= n;

		len += n;
	}
	return len;
fail:
	return n;
}