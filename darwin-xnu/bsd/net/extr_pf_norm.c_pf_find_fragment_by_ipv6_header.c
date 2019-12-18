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
struct pf_fragment {int dummy; } ;
struct pf_frag_tree {int dummy; } ;
struct ip6_hdr {int dummy; } ;
struct ip6_frag {int dummy; } ;

/* Variables and functions */
 struct pf_fragment* pf_find_fragment_by_key (struct pf_fragment*,struct pf_frag_tree*) ; 
 int /*<<< orphan*/  pf_ip6hdr2key (struct pf_fragment*,struct ip6_hdr*,struct ip6_frag*) ; 

__attribute__((used)) static __inline struct pf_fragment *
pf_find_fragment_by_ipv6_header(struct ip6_hdr *ip6, struct ip6_frag *fh,
    struct pf_frag_tree *tree)
{
      struct pf_fragment key;
      pf_ip6hdr2key(&key, ip6, fh);
      return pf_find_fragment_by_key(&key, tree);
}