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
typedef  int /*<<< orphan*/  u_char ;
struct inpcb {int inp_vflag; int /*<<< orphan*/  inp_faddr; int /*<<< orphan*/  in6p_faddr; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int CCAES_BLOCK_SIZE ; 
 int INP_IPV6 ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  aes_encrypt_cbc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tfo_ctx ; 

void
tcp_tfo_gen_cookie(struct inpcb *inp, u_char *out, size_t blk_size)
{
	u_char in[CCAES_BLOCK_SIZE];
#if INET6
	int isipv6 = inp->inp_vflag & INP_IPV6;
#endif

	VERIFY(blk_size == CCAES_BLOCK_SIZE);

	bzero(&in[0], CCAES_BLOCK_SIZE);
	bzero(&out[0], CCAES_BLOCK_SIZE);

#if INET6
	if (isipv6)
		memcpy(in, &inp->in6p_faddr, sizeof(struct in6_addr));
	else
#endif /* INET6 */
		memcpy(in, &inp->inp_faddr, sizeof(struct in_addr));

	aes_encrypt_cbc(in, NULL, 1, out, &tfo_ctx);
}