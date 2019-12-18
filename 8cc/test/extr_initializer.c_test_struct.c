__attribute__((used)) static void test_struct() {
    int we[] = { 1, 0, 0, 0, 2, 0, 0, 0 };
    struct { int a[3]; int b; } w[] = { { 1 }, 2 };
    verify(we, &w, 8);
}