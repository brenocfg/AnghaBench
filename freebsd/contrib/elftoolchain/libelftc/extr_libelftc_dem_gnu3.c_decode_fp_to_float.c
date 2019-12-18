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

/* Variables and functions */
 size_t BUFFER_GROWFACTOR ; 
 int /*<<< orphan*/  FLOAT_SPRINTF_TRY_LIMIT ; 
 int /*<<< orphan*/  free (char*) ; 
 int hex_to_dec (char const) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 
 int snprintf (char*,size_t,char*,float) ; 

__attribute__((used)) static char *
decode_fp_to_float(const char *p, size_t len)
{
	size_t i, rtn_len, limit;
	float f;
	int byte;
	char *rtn;

	if (p == NULL || len == 0 || len % 2 != 0 || len / 2 > sizeof(float))
		return (NULL);

	memset(&f, 0, sizeof(float));

	for (i = 0; i < len / 2; ++i) {
		byte = hex_to_dec(p[len - i * 2 - 1]) +
		    hex_to_dec(p[len - i * 2 - 2]) * 16;
		if (byte < 0 || byte > 255)
			return (NULL);
#if ELFTC_BYTE_ORDER == ELFTC_BYTE_ORDER_LITTLE_ENDIAN
		((unsigned char *)&f)[i] = (unsigned char)(byte);
#else /* ELFTC_BYTE_ORDER != ELFTC_BYTE_ORDER_LITTLE_ENDIAN */
		((unsigned char *)&f)[sizeof(float) - i - 1] =
		    (unsigned char)(byte);
#endif /* ELFTC_BYTE_ORDER == ELFTC_BYTE_ORDER_LITTLE_ENDIAN */
	}

	rtn_len = 64;
	limit = 0;
again:
	if ((rtn = malloc(sizeof(char) * rtn_len)) == NULL)
		return (NULL);

	if (snprintf(rtn, rtn_len, "%ff", f) >= (int)rtn_len) {
		free(rtn);
		if (limit++ > FLOAT_SPRINTF_TRY_LIMIT)
			return (NULL);
		rtn_len *= BUFFER_GROWFACTOR;
		goto again;
	}

	return rtn;
}