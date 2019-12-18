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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;

/* Variables and functions */
 int /*<<< orphan*/  BLEND_OP (int,scalar_t__*) ; 
 scalar_t__ Ch (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LOAD_OP (int,scalar_t__*,int /*<<< orphan*/  const*) ; 
 scalar_t__ Maj (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ e0 (scalar_t__) ; 
 scalar_t__ e1 (scalar_t__) ; 
 scalar_t__* get_cpu_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_schedule ; 
 int /*<<< orphan*/  put_cpu_var (int /*<<< orphan*/ ) ; 
 scalar_t__* sha512_K ; 

__attribute__((used)) static void
sha512_transform(u64 *state, const u8 *input)
{
	u64 a, b, c, d, e, f, g, h, t1, t2;

	int i;
	u64 *W = get_cpu_var(msg_schedule);

	/* load the input */
        for (i = 0; i < 16; i++)
                LOAD_OP(i, W, input);

        for (i = 16; i < 80; i++) {
                BLEND_OP(i, W);
        }

	/* load the state into our registers */
	a=state[0];   b=state[1];   c=state[2];   d=state[3];
	e=state[4];   f=state[5];   g=state[6];   h=state[7];

	/* now iterate */
	for (i=0; i<80; i+=8) {
		t1 = h + e1(e) + Ch(e,f,g) + sha512_K[i  ] + W[i  ];
		t2 = e0(a) + Maj(a,b,c);    d+=t1;    h=t1+t2;
		t1 = g + e1(d) + Ch(d,e,f) + sha512_K[i+1] + W[i+1];
		t2 = e0(h) + Maj(h,a,b);    c+=t1;    g=t1+t2;
		t1 = f + e1(c) + Ch(c,d,e) + sha512_K[i+2] + W[i+2];
		t2 = e0(g) + Maj(g,h,a);    b+=t1;    f=t1+t2;
		t1 = e + e1(b) + Ch(b,c,d) + sha512_K[i+3] + W[i+3];
		t2 = e0(f) + Maj(f,g,h);    a+=t1;    e=t1+t2;
		t1 = d + e1(a) + Ch(a,b,c) + sha512_K[i+4] + W[i+4];
		t2 = e0(e) + Maj(e,f,g);    h+=t1;    d=t1+t2;
		t1 = c + e1(h) + Ch(h,a,b) + sha512_K[i+5] + W[i+5];
		t2 = e0(d) + Maj(d,e,f);    g+=t1;    c=t1+t2;
		t1 = b + e1(g) + Ch(g,h,a) + sha512_K[i+6] + W[i+6];
		t2 = e0(c) + Maj(c,d,e);    f+=t1;    b=t1+t2;
		t1 = a + e1(f) + Ch(f,g,h) + sha512_K[i+7] + W[i+7];
		t2 = e0(b) + Maj(b,c,d);    e+=t1;    a=t1+t2;
	}

	state[0] += a; state[1] += b; state[2] += c; state[3] += d;
	state[4] += e; state[5] += f; state[6] += g; state[7] += h;

	/* erase our data */
	a = b = c = d = e = f = g = h = t1 = t2 = 0;
	memset(W, 0, sizeof(__get_cpu_var(msg_schedule)));
	put_cpu_var(msg_schedule);
}