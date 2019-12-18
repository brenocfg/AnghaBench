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
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;
typedef  int /*<<< orphan*/  ctf_encoding_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_K_FLOAT ; 
 int /*<<< orphan*/  ctf_add_encoded (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

ctf_id_t
ctf_add_float(ctf_file_t *fp, uint_t flag,
    const char *name, const ctf_encoding_t *ep)
{
	return (ctf_add_encoded(fp, flag, name, ep, CTF_K_FLOAT));
}