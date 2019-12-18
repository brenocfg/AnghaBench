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
typedef  scalar_t__ u32 ;
struct tcp_sock {scalar_t__ packets_out; int fackets_out; scalar_t__ max_window; scalar_t__ snd_una; scalar_t__ high_seq; scalar_t__ frto_highmark; scalar_t__ retrans_out; scalar_t__ lost_out; scalar_t__ sacked_out; scalar_t__ undo_marker; struct tcp_sack_block* recv_sack_cache; } ;
struct tcp_sacktag_state {int flag; scalar_t__ reord; int fack_count; } ;
struct tcp_sack_block_wire {int /*<<< orphan*/  end_seq; int /*<<< orphan*/  start_seq; } ;
struct tcp_sack_block {scalar_t__ start_seq; scalar_t__ end_seq; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct inet_connection_sock {scalar_t__ icsk_ca_state; } ;
struct TYPE_2__ {int sacked; scalar_t__ ack_seq; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct tcp_sack_block*) ; 
 int FLAG_DATA_LOST ; 
 int FLAG_DSACKING_ACK ; 
 int FLAG_ONLY_ORIG_SACKED ; 
 int LINUX_MIB_TCPDSACKIGNOREDNOUNDO ; 
 int LINUX_MIB_TCPDSACKIGNOREDOLD ; 
 int LINUX_MIB_TCPSACKDISCARD ; 
 int /*<<< orphan*/  NET_INC_STATS_BH (int /*<<< orphan*/ ,int) ; 
 unsigned char TCPOLEN_SACK_BASE ; 
 scalar_t__ TCP_CA_Loss ; 
 int TCP_NUM_SACKS ; 
 TYPE_1__* TCP_SKB_CB (struct sk_buff*) ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ after (scalar_t__,scalar_t__) ; 
 scalar_t__ before (scalar_t__,scalar_t__) ; 
 void* get_unaligned_be32 (int /*<<< orphan*/ *) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int min (int,unsigned char) ; 
 unsigned char* skb_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  swap (struct tcp_sack_block,struct tcp_sack_block) ; 
 int tcp_check_dsack (struct sock*,struct sk_buff*,struct tcp_sack_block_wire*,int,scalar_t__) ; 
 struct sk_buff* tcp_highest_sack (struct sock*) ; 
 int /*<<< orphan*/  tcp_highest_sack_reset (struct sock*) ; 
 scalar_t__ tcp_highest_sack_seq (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_is_sackblock_valid (struct tcp_sock*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tcp_mark_lost_retrans (struct sock*) ; 
 struct sk_buff* tcp_maybe_skipping_dsack (struct sk_buff*,struct sock*,struct tcp_sack_block*,struct tcp_sacktag_state*,scalar_t__) ; 
 scalar_t__ tcp_packets_in_flight (struct tcp_sock*) ; 
 scalar_t__ tcp_sack_cache_ok (struct tcp_sock*,struct tcp_sack_block*) ; 
 struct sk_buff* tcp_sacktag_skip (struct sk_buff*,struct sock*,struct tcp_sacktag_state*,scalar_t__) ; 
 struct sk_buff* tcp_sacktag_walk (struct sk_buff*,struct sock*,struct tcp_sack_block*,struct tcp_sacktag_state*,scalar_t__,scalar_t__,int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_update_reordering (struct sock*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_verify_left_out (struct tcp_sock*) ; 
 struct sk_buff* tcp_write_queue_head (struct sock*) ; 

__attribute__((used)) static int
tcp_sacktag_write_queue(struct sock *sk, struct sk_buff *ack_skb,
			u32 prior_snd_una)
{
	const struct inet_connection_sock *icsk = inet_csk(sk);
	struct tcp_sock *tp = tcp_sk(sk);
	unsigned char *ptr = (skb_transport_header(ack_skb) +
			      TCP_SKB_CB(ack_skb)->sacked);
	struct tcp_sack_block_wire *sp_wire = (struct tcp_sack_block_wire *)(ptr+2);
	struct tcp_sack_block sp[TCP_NUM_SACKS];
	struct tcp_sack_block *cache;
	struct tcp_sacktag_state state;
	struct sk_buff *skb;
	int num_sacks = min(TCP_NUM_SACKS, (ptr[1] - TCPOLEN_SACK_BASE) >> 3);
	int used_sacks;
	int found_dup_sack = 0;
	int i, j;
	int first_sack_index;

	state.flag = 0;
	state.reord = tp->packets_out;

	if (!tp->sacked_out) {
		if (WARN_ON(tp->fackets_out))
			tp->fackets_out = 0;
		tcp_highest_sack_reset(sk);
	}

	found_dup_sack = tcp_check_dsack(sk, ack_skb, sp_wire,
					 num_sacks, prior_snd_una);
	if (found_dup_sack)
		state.flag |= FLAG_DSACKING_ACK;

	/* Eliminate too old ACKs, but take into
	 * account more or less fresh ones, they can
	 * contain valid SACK info.
	 */
	if (before(TCP_SKB_CB(ack_skb)->ack_seq, prior_snd_una - tp->max_window))
		return 0;

	if (!tp->packets_out)
		goto out;

	used_sacks = 0;
	first_sack_index = 0;
	for (i = 0; i < num_sacks; i++) {
		int dup_sack = !i && found_dup_sack;

		sp[used_sacks].start_seq = get_unaligned_be32(&sp_wire[i].start_seq);
		sp[used_sacks].end_seq = get_unaligned_be32(&sp_wire[i].end_seq);

		if (!tcp_is_sackblock_valid(tp, dup_sack,
					    sp[used_sacks].start_seq,
					    sp[used_sacks].end_seq)) {
			int mib_idx;

			if (dup_sack) {
				if (!tp->undo_marker)
					mib_idx = LINUX_MIB_TCPDSACKIGNOREDNOUNDO;
				else
					mib_idx = LINUX_MIB_TCPDSACKIGNOREDOLD;
			} else {
				/* Don't count olds caused by ACK reordering */
				if ((TCP_SKB_CB(ack_skb)->ack_seq != tp->snd_una) &&
				    !after(sp[used_sacks].end_seq, tp->snd_una))
					continue;
				mib_idx = LINUX_MIB_TCPSACKDISCARD;
			}

			NET_INC_STATS_BH(sock_net(sk), mib_idx);
			if (i == 0)
				first_sack_index = -1;
			continue;
		}

		/* Ignore very old stuff early */
		if (!after(sp[used_sacks].end_seq, prior_snd_una))
			continue;

		used_sacks++;
	}

	/* order SACK blocks to allow in order walk of the retrans queue */
	for (i = used_sacks - 1; i > 0; i--) {
		for (j = 0; j < i; j++) {
			if (after(sp[j].start_seq, sp[j + 1].start_seq)) {
				swap(sp[j], sp[j + 1]);

				/* Track where the first SACK block goes to */
				if (j == first_sack_index)
					first_sack_index = j + 1;
			}
		}
	}

	skb = tcp_write_queue_head(sk);
	state.fack_count = 0;
	i = 0;

	if (!tp->sacked_out) {
		/* It's already past, so skip checking against it */
		cache = tp->recv_sack_cache + ARRAY_SIZE(tp->recv_sack_cache);
	} else {
		cache = tp->recv_sack_cache;
		/* Skip empty blocks in at head of the cache */
		while (tcp_sack_cache_ok(tp, cache) && !cache->start_seq &&
		       !cache->end_seq)
			cache++;
	}

	while (i < used_sacks) {
		u32 start_seq = sp[i].start_seq;
		u32 end_seq = sp[i].end_seq;
		int dup_sack = (found_dup_sack && (i == first_sack_index));
		struct tcp_sack_block *next_dup = NULL;

		if (found_dup_sack && ((i + 1) == first_sack_index))
			next_dup = &sp[i + 1];

		/* Event "B" in the comment above. */
		if (after(end_seq, tp->high_seq))
			state.flag |= FLAG_DATA_LOST;

		/* Skip too early cached blocks */
		while (tcp_sack_cache_ok(tp, cache) &&
		       !before(start_seq, cache->end_seq))
			cache++;

		/* Can skip some work by looking recv_sack_cache? */
		if (tcp_sack_cache_ok(tp, cache) && !dup_sack &&
		    after(end_seq, cache->start_seq)) {

			/* Head todo? */
			if (before(start_seq, cache->start_seq)) {
				skb = tcp_sacktag_skip(skb, sk, &state,
						       start_seq);
				skb = tcp_sacktag_walk(skb, sk, next_dup,
						       &state,
						       start_seq,
						       cache->start_seq,
						       dup_sack);
			}

			/* Rest of the block already fully processed? */
			if (!after(end_seq, cache->end_seq))
				goto advance_sp;

			skb = tcp_maybe_skipping_dsack(skb, sk, next_dup,
						       &state,
						       cache->end_seq);

			/* ...tail remains todo... */
			if (tcp_highest_sack_seq(tp) == cache->end_seq) {
				/* ...but better entrypoint exists! */
				skb = tcp_highest_sack(sk);
				if (skb == NULL)
					break;
				state.fack_count = tp->fackets_out;
				cache++;
				goto walk;
			}

			skb = tcp_sacktag_skip(skb, sk, &state, cache->end_seq);
			/* Check overlap against next cached too (past this one already) */
			cache++;
			continue;
		}

		if (!before(start_seq, tcp_highest_sack_seq(tp))) {
			skb = tcp_highest_sack(sk);
			if (skb == NULL)
				break;
			state.fack_count = tp->fackets_out;
		}
		skb = tcp_sacktag_skip(skb, sk, &state, start_seq);

walk:
		skb = tcp_sacktag_walk(skb, sk, next_dup, &state,
				       start_seq, end_seq, dup_sack);

advance_sp:
		/* SACK enhanced FRTO (RFC4138, Appendix B): Clearing correct
		 * due to in-order walk
		 */
		if (after(end_seq, tp->frto_highmark))
			state.flag &= ~FLAG_ONLY_ORIG_SACKED;

		i++;
	}

	/* Clear the head of the cache sack blocks so we can skip it next time */
	for (i = 0; i < ARRAY_SIZE(tp->recv_sack_cache) - used_sacks; i++) {
		tp->recv_sack_cache[i].start_seq = 0;
		tp->recv_sack_cache[i].end_seq = 0;
	}
	for (j = 0; j < used_sacks; j++)
		tp->recv_sack_cache[i++] = sp[j];

	tcp_mark_lost_retrans(sk);

	tcp_verify_left_out(tp);

	if ((state.reord < tp->fackets_out) &&
	    ((icsk->icsk_ca_state != TCP_CA_Loss) || tp->undo_marker) &&
	    (!tp->frto_highmark || after(tp->snd_una, tp->frto_highmark)))
		tcp_update_reordering(sk, tp->fackets_out - state.reord, 0);

out:

#if FASTRETRANS_DEBUG > 0
	WARN_ON((int)tp->sacked_out < 0);
	WARN_ON((int)tp->lost_out < 0);
	WARN_ON((int)tp->retrans_out < 0);
	WARN_ON((int)tcp_packets_in_flight(tp) < 0);
#endif
	return state.flag;
}