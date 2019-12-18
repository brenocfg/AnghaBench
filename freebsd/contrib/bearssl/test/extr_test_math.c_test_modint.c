#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  mpz_t ;
struct TYPE_2__ {int (* decode_mod ) (int*,unsigned char*,size_t,int*) ;int (* ninv ) (int) ;int (* add ) (int*,int*,int) ;int (* sub ) (int*,int*,int) ;int word_size; int /*<<< orphan*/  (* modpow ) (int*,unsigned char*,size_t,int*,int,int*,int*) ;int /*<<< orphan*/  (* montymul ) (int*,int*,int*,int*,int) ;int /*<<< orphan*/  (* to_monty ) (int*,int*) ;int /*<<< orphan*/  (* from_monty ) (int*,int*,int) ;int /*<<< orphan*/  (* reduce ) (int*,int*,int*) ;int /*<<< orphan*/  (* decode ) (int*,unsigned char*,size_t) ;int /*<<< orphan*/  (* decode_reduce ) (int*,unsigned char*,size_t,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  RNG ; 
 int /*<<< orphan*/  check_eqz (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gmp_randinit_mt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gmp_randseed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* impl ; 
 int /*<<< orphan*/  mpz_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_export (unsigned char*,size_t*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_mod (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_mul_2exp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpz_powm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_set_ui (int /*<<< orphan*/ ,int) ; 
 scalar_t__ mpz_sgn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpz_urandomb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpz_urandomm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_u (int*) ; 
 int /*<<< orphan*/  print_z (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  rand_prime (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  stub1 (int*,unsigned char*,size_t) ; 
 int stub10 (int*,int*,int) ; 
 int stub11 (int*,unsigned char*,size_t,int*) ; 
 int stub12 (int*,unsigned char*,size_t,int*) ; 
 int stub13 (int*,int*,int) ; 
 int stub14 (int*,int*,int) ; 
 int /*<<< orphan*/  stub15 (int*,unsigned char*,size_t,int*) ; 
 int /*<<< orphan*/  stub16 (int*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub17 (int*,int*,int*) ; 
 int stub18 (int*,unsigned char*,size_t,int*) ; 
 int /*<<< orphan*/  stub19 (int*,int*) ; 
 int stub2 (int*,unsigned char*,size_t,int*) ; 
 int /*<<< orphan*/  stub20 (int*,int*,int) ; 
 int stub21 (int*,unsigned char*,size_t,int*) ; 
 int stub22 (int*,unsigned char*,size_t,int*) ; 
 int /*<<< orphan*/  stub23 (int*,int*) ; 
 int /*<<< orphan*/  stub24 (int*,int*,int*,int*,int) ; 
 int stub25 (int*,unsigned char*,size_t,int*) ; 
 int /*<<< orphan*/  stub26 (int*,unsigned char*,size_t,int*,int,int*,int*) ; 
 int stub3 (int) ; 
 int stub4 (int*,unsigned char*,size_t,int*) ; 
 int /*<<< orphan*/  stub5 (int*,unsigned char*,size_t) ; 
 int stub6 (int*,unsigned char*,size_t,int*) ; 
 int stub7 (int*,unsigned char*,size_t,int*) ; 
 int stub8 (int*,int*,int) ; 
 int stub9 (int*,int*,int) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_modint(void)
{
	int i, j, k;
	mpz_t p, a, b, v, t1;

	printf("Test modular integers: ");
	fflush(stdout);

	gmp_randinit_mt(RNG);
	mpz_init(p);
	mpz_init(a);
	mpz_init(b);
	mpz_init(v);
	mpz_init(t1);
	mpz_set_ui(t1, (unsigned long)time(NULL));
	gmp_randseed(RNG, t1);
	for (k = 2; k <= 128; k ++) {
		for (i = 0; i < 10; i ++) {
			unsigned char ep[100], ea[100], eb[100], ev[100];
			size_t plen, alen, blen, vlen;
			uint32_t mp[40], ma[40], mb[40], mv[60], mx[100];
			uint32_t mt1[40], mt2[40], mt3[40];
			uint32_t ctl;
			uint32_t mp0i;

			rand_prime(p, k);
			mpz_urandomm(a, RNG, p);
			mpz_urandomm(b, RNG, p);
			mpz_urandomb(v, RNG, k + 60);
			if (mpz_sgn(b) == 0) {
				mpz_set_ui(b, 1);
			}
			mpz_export(ep, &plen, 1, 1, 0, 0, p);
			mpz_export(ea, &alen, 1, 1, 0, 0, a);
			mpz_export(eb, &blen, 1, 1, 0, 0, b);
			mpz_export(ev, &vlen, 1, 1, 0, 0, v);

			impl->decode(mp, ep, plen);
			if (impl->decode_mod(ma, ea, alen, mp) != 1) {
				printf("Decode error\n");
				printf("  ea = ");
				print_z(a);
				printf("\n");
				printf("  p = ");
				print_u(mp);
				printf("\n");
				exit(EXIT_FAILURE);
			}
			mp0i = impl->ninv(mp[1]);
			if (impl->decode_mod(mb, eb, blen, mp) != 1) {
				printf("Decode error\n");
				printf("  eb = ");
				print_z(b);
				printf("\n");
				printf("  p = ");
				print_u(mp);
				printf("\n");
				exit(EXIT_FAILURE);
			}
			impl->decode(mv, ev, vlen);
			check_eqz(mp, p);
			check_eqz(ma, a);
			check_eqz(mb, b);
			check_eqz(mv, v);

			impl->decode_mod(ma, ea, alen, mp);
			impl->decode_mod(mb, eb, blen, mp);
			ctl = impl->add(ma, mb, 1);
			ctl |= impl->sub(ma, mp, 0) ^ (uint32_t)1;
			impl->sub(ma, mp, ctl);
			mpz_add(t1, a, b);
			mpz_mod(t1, t1, p);
			check_eqz(ma, t1);

			impl->decode_mod(ma, ea, alen, mp);
			impl->decode_mod(mb, eb, blen, mp);
			impl->add(ma, mp, impl->sub(ma, mb, 1));
			mpz_sub(t1, a, b);
			mpz_mod(t1, t1, p);
			check_eqz(ma, t1);

			impl->decode_reduce(ma, ev, vlen, mp);
			mpz_mod(t1, v, p);
			check_eqz(ma, t1);

			impl->decode(mv, ev, vlen);
			impl->reduce(ma, mv, mp);
			mpz_mod(t1, v, p);
			check_eqz(ma, t1);

			impl->decode_mod(ma, ea, alen, mp);
			impl->to_monty(ma, mp);
			mpz_mul_2exp(t1, a, ((k + impl->word_size - 1)
				/ impl->word_size) * impl->word_size);
			mpz_mod(t1, t1, p);
			check_eqz(ma, t1);
			impl->from_monty(ma, mp, mp0i);
			check_eqz(ma, a);

			impl->decode_mod(ma, ea, alen, mp);
			impl->decode_mod(mb, eb, blen, mp);
			impl->to_monty(ma, mp);
			impl->montymul(mt1, ma, mb, mp, mp0i);
			mpz_mul(t1, a, b);
			mpz_mod(t1, t1, p);
			check_eqz(mt1, t1);

			impl->decode_mod(ma, ea, alen, mp);
			impl->modpow(ma, ev, vlen, mp, mp0i, mt1, mt2);
			mpz_powm(t1, a, v, p);
			check_eqz(ma, t1);

			/*
			br_modint_decode(ma, mp, ea, alen);
			br_modint_decode(mb, mp, eb, blen);
			if (!br_modint_div(ma, mb, mp, mt1, mt2, mt3)) {
				fprintf(stderr, "division failed\n");
				exit(EXIT_FAILURE);
			}
			mpz_sub_ui(t1, p, 2);
			mpz_powm(t1, b, t1, p);
			mpz_mul(t1, a, t1);
			mpz_mod(t1, t1, p);
			check_eqz(ma, t1);

			br_modint_decode(ma, mp, ea, alen);
			br_modint_decode(mb, mp, eb, blen);
			for (j = 0; j <= (2 * k + 5); j ++) {
				br_int_add(mx, j, ma, mb);
				mpz_add(t1, a, b);
				mpz_tdiv_r_2exp(t1, t1, j);
				check_eqz(mx, t1);

				br_int_mul(mx, j, ma, mb);
				mpz_mul(t1, a, b);
				mpz_tdiv_r_2exp(t1, t1, j);
				check_eqz(mx, t1);
			}
			*/
		}
		printf(".");
		fflush(stdout);
	}
	mpz_clear(p);
	mpz_clear(a);
	mpz_clear(b);
	mpz_clear(v);
	mpz_clear(t1);

	printf(" done.\n");
	fflush(stdout);
}