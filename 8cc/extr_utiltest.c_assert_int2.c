__attribute__((used)) static void assert_int2(int line, long a, long b) {
    if (a != b)
        error("%d: Expected %ld but got %ld", line, a, b);
}